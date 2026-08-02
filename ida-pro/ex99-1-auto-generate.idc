#include <idc.idc>

static set_enabled(attr, value) {
	set_inf_attr(attr, get_inf_attr(attr) | (value));
}

static set_disabled(attr, value) {
	set_inf_attr(attr, get_inf_attr(attr) & ~(value));
}

static generate_file(fname, name, action, subaction) {
	Message("Generating %s...\n", name);
	auto fp = fopen(fname, "w");
	if (fp) {
		Message("Creating %s[%s] output file...\n", name, fname);
		gen_file(action, fp, 0, BADADDR, subaction);
		fclose(fp);
	}
	Message("All done, exiting...\n");
}

static config() {
//	set_processor_type("k62", SETPROC_USER);		// AMD K6-2
//	set_target_assembler(0);						// 0 = Intel 80x80, 1 = Borland TASM

	process_config_directive("OPCODE_BYTES=10");
	process_config_directive("GRAPH_OPCODE_BYTES=10");
	//process_config_directive("ABANDON_DATABASE=YES");

	set_enabled(INF_AF, AF_MARKCODE);				// Mark typical code sequences as code.
	set_enabled(INF_AF, AF_PROC);					// Create functions if call is present.
	set_enabled(INF_AF, AF_DODATA);					// Coagulate code segs at the final pass.
	set_disabled(INF_AF, AF_UNK);					// Delete instructions with no xrefs.
	set_disabled(INF_AF, AF_HFLIRT);				// Automatically hide library functions.
}

static save_asm(fname, yes) {
	generate_file(fname, "ASM", OFILE_ASM, yes ? GENFLG_ASMTYPE : 0);
}

static save_lst(fname) {
	generate_file(fname, "ASM", OFILE_LST, 0);
}

static save_map(fname, yes) {
	generate_file(fname, "MAP", OFILE_MAP, yes ? GENFLG_MAPSEGS : GENFLG_MAPNAME | GENFLG_MAPDMNG | GENFLG_MAPLOC);
}

static save_infos(fp, name, value) {
	if (fp) {
		fprintf(fp, "    %-12s = %s\n", name, value);
	}
}

static save_infocreate(value) {
	return value ? "yes" : "no";
}

static save_infob(fp, name, attr, value) {
	save_infos(fp, name, save_infocreate(get_inf_attr(attr) & value));
}

static save_infoe(fp, name, attr, value) {
	save_infos(fp, name, save_infocreate(get_inf_attr(attr) == value));
}

static save_infom(fp, name, attr, mask, value) {
	save_infos(fp, name, save_infocreate((get_inf_attr(attr) & mask) == value));
}

static save_general(fp) {
	if (fp) {
		fprintf(fp, "GENERAL\n");
		save_infos(fp, "FILE", get_input_file_path());
	}
}

static save_segments(fp) {
	if (fp) {
		auto seg = get_first_seg();
		while (seg != BADADDR) {
			msg("segment: %-20s start: %08x end: %08x\n",
				get_segm_name(seg),
				get_segm_attr(seg, SEGATTR_START),
				get_segm_attr(seg, SEGATTR_END));

			// do looping here
			seg = get_next_seg(seg);
		}

		msg("%-20s\n", get_name(0));
	}
}

static save_filetype(fp) {
	auto x = object();			auto y = object();
	x[0] = "FT_BIN";			y[0] = FT_BIN;				x[1] = "FT_DRV";			y[1] = FT_DRV;			x[2] = "FT_WIN";			y[2] = FT_WIN;
	x[3] = "FT_HEX";			y[3] = FT_HEX;				x[4] = "FT_MEX";			y[4] = FT_MEX;			x[5] = "FT_LX";				y[5] = FT_LX;
	x[6] = "FT_LE";				y[6] = FT_LE;				x[7] = "FT_NLM";			y[7] = FT_NLM;			x[8] = "FT_COFF";			y[8] = FT_COFF;
	x[9] = "FT_PE";				y[9] = FT_PE;				x[10] = "FT_OMF";			y[10] = FT_OMF;			x[11] = "FT_SREC";			y[11] = FT_SREC;
	x[12] = "FT_ZIP";			y[12] = FT_ZIP;				x[13] = "FT_OMFLIB";		y[13] = FT_OMFLIB;		x[14] = "FT_AR";			y[14] = FT_AR;
	x[15] = "FT_LOADER";		y[15] = FT_LOADER;			x[16] = "FT_ELF";			y[16] = FT_ELF;			x[17] = "FT_W32RUN";		y[17] = FT_W32RUN;
	x[18] = "FT_AOUT";			y[18] = FT_AOUT;			x[19] = "FT_PRC";			y[19] = FT_PRC;			x[20] = "FT_EXE";			y[20] = FT_EXE;
	x[21] = "FT_COM";			y[21] = FT_COM;				x[22] = "FT_AIXAR";			y[22] = FT_AIXAR;		x[23] = "FT_MACHO";			y[23] = FT_MACHO;

	if (fp) {
		auto i;
		fprintf(fp, "INF_FILETYPE\n");
		for (i = 0; i < 24; i = i + 1) {
			save_infoe(fp, x[i], INF_FILETYPE, y[i]);
		}
	}
}

static save_ostype(fp) {
	auto x = object();			auto y = object();
	x[0] = "OSTYPE_MSDOS";		y[0] = OSTYPE_MSDOS;		x[1] = "OSTYPE_WIN";		y[1] = OSTYPE_WIN;		x[2] = "OSTYPE_OS2";		y[2] = OSTYPE_OS2;
	x[3] = "OSTYPE_NETW";		y[3] = OSTYPE_NETW;

	if (fp) {
		auto i;
		fprintf(fp, "INF_OSTYPE\n");
		for (i = 0; i < 4; i = i + 1) {
			save_infoe(fp, x[i], INF_OSTYPE, y[i]);
		}
	}
}

static save_ccid(fp) {
	auto x = object();			auto y = object();
	x[0] = "COMP_UNK";			y[0] = COMP_UNK;			x[1] = "COMP_MS";			y[1] = COMP_MS;			x[2] = "COMP_BC";			y[2] = COMP_BC;
	x[3] = "COMP_WATCOM";		y[3] = COMP_WATCOM;			x[4] = "COMP_GNU";			y[4] = COMP_GNU;		x[5] = "COMP_VISAGE";		y[5] = COMP_VISAGE;
	x[6] = "COMP_BP";			y[6] = COMP_BP;

	if (fp) {
		auto i;
		fprintf(fp, "INF_CC_ID\n");
		for (i = 0; i < 7; i = i + 1) {
			save_infom(fp, x[i], INF_CC_ID, COMP_MASK, y[i]);
		}
	}
}

static save_af1(fp) {
	auto x = object();			auto y = object();
	x[0] = "AF_CODE";			y[0] = AF_CODE;				x[1] = "AF_MARKCODE";		y[1] = AF_MARKCODE;		x[2] = "AF_JUMPTBL";		y[2] = AF_JUMPTBL;
	x[3] = "AF_PURDAT";			y[3] = AF_PURDAT;			x[4] = "AF_USED";			y[4] = AF_USED;			x[5] = "AF_UNK";			y[5] = AF_UNK;
	x[6] = "AF_PROCPTR";		y[6] = AF_PROCPTR;			x[7] = "AF_PROC";			y[7] = AF_PROC;			x[8] = "AF_FTAIL";			y[8] = AF_FTAIL;
	x[9] = "AF_LVAR";			y[9] = AF_LVAR;				x[10] = "AF_STKARG";		y[10] = AF_STKARG;		x[11] = "AF_REGARG";		y[11] = AF_REGARG;
	x[12] = "AF_TRACE";			y[12] = AF_TRACE;			x[13] = "AF_VERSP";			y[13] = AF_VERSP;		x[14] = "AF_ANORET";		y[14] = AF_ANORET;
	x[15] = "AF_MEMFUNC";		y[15] = AF_MEMFUNC;			x[16] = "AF_TRFUNC";		y[16] = AF_TRFUNC;		x[17] = "AF_STRLIT";		y[17] = AF_STRLIT;
	x[18] = "AF_CHKUNI";		y[18] = AF_CHKUNI;			x[19] = "AF_FIXUP";			y[19] = AF_FIXUP;		x[20] = "AF_DREFOFF";		y[20] = AF_DREFOFF;
	x[21] = "AF_IMMOFF";		y[21] = AF_IMMOFF;			x[22] = "AF_DATOFF";		y[22] = AF_DATOFF;		x[23] = "AF_FLIRT";			y[23] = AF_FLIRT;
	x[24] = "AF_SIGCMT";		y[24] = AF_SIGCMT;			x[25] = "AF_SIGMLT";		y[25] = AF_SIGMLT;		x[26] = "AF_HFLIRT";		y[26] = AF_HFLIRT;
	x[27] = "AF_JFUNC";			y[27] = AF_JFUNC;			x[28] = "AF_NULLSUB";		y[28] = AF_NULLSUB;		x[29] = "AF_DODATA";		y[29] = AF_DODATA;
	x[30] = "AF_DOCODE";		y[30] = AF_DOCODE;			x[31] = "AF_FINAL";			y[31] = AF_FINAL;

	if (fp) {
		auto i;
		fprintf(fp, "INF_AF\n");
		for (i = 0; i < 32; i = i + 1) {
			save_infob(fp, x[i], INF_AF, y[i]);
		}
	}
}

static save_af2(fp) {
	auto x = object();			auto y = object();
	x[0] = "AF2_DOEH";			y[0] = AF2_DOEH;			x[1] = "AF2_DORTTI";		y[1] = AF2_DORTTI;		x[2] = "AF2_MACRO";			y[2] = AF2_MACRO;

	if (fp) {
		auto i;
		fprintf(fp, "INF_AF2\n");
		for (i = 0; i < 3; i = i + 1) {
			save_infob(fp, x[i], INF_AF2, y[i]);
		}
	}
}

static save_info(fname) {
	auto fp = fopen(fname, "w");
	if (fp) {
		save_general(fp);
		save_segments(fp);
		save_filetype(fp);
		save_ostype(fp);
		save_ccid(fp);
		save_af1(fp);
		save_af2(fp);

		fclose(fp);
	}
}

static main() {

	auto FALSE = 0;
	auto TRUE  = 1;

//	ARGV.count = 6;
//	ARGV[1] = "--noasm";
//	ARGV[2] = "--nolst";
//	ARGV[3] = "--nomap";
//	ARGV[5] = "--noDef";
//	ARGV[6] = "--name=outfile.txt";
//	ARGV[7] = "--exit";

	auto doasm = TRUE;
	auto dolst = TRUE;
	auto domap = TRUE;
	auto dodef = TRUE;
	auto closedown = FALSE;
	auto outname = get_input_file_path();

	if (ARGV.count < 2) {
		Message("Hello World from IDC\n");
	} else {

		auto i;
		for (i = 0; i < ARGV.count; i = i + 1) {

			if (strlen(ARGV[i]) < 3)		continue;
			if (ARGV[i][0:2] != "--")		continue;

			auto arg = tolower(ARGV[i][2:]);

			if (arg == "exit")		closedown = TRUE;
			if (arg[:5] == "name=")	outname = ARGV[i][7:];

			if (arg == "noasm")		doasm = FALSE;
			if (arg == "nolst")		dolst = FALSE;
			if (arg == "nomap")		domap = FALSE;
			if (arg == "nodef")		dodef = FALSE;
		}
	}

	Message("OUTNAME: %s\n", outname);
	Message("NODEF:   %d\n", !dodef);
	Message("NOASM:   %d\n", !doasm);
	Message("NOLST:   %d\n", !dolst);
	Message("NOMAP:   %d\n", !domap);
	Message("EXIT:    %d\n", closedown);

	config();

	if (doasm || domap || dolst) {
		Message("Waiting for the end of auto analysis to finish...\n");
		auto_wait();
	}

	save_info(outname + ".info");

	if (doasm)			save_asm(outname + ".asm", dodef);
	if (domap)			save_map(outname + ".map", dodef);
	if (dolst)			save_lst(outname + ".lst");

	Message("Completed script...\n");

	if (closedown)
		qexit(0); // Exit IDA Pro

	return 0;
}

