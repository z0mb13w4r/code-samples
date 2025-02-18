#include <bfd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if (argc == 2) {
    bfd_init();

    bfd *f = bfd_openr(argv[1], NULL);
    if (f) {
      printf("opened file '%s' for analysis.\n", argv[1]);
      if (!bfd_check_format(f, bfd_object)) {
        printf("ERROR: file '%s' does not look like an executable (%s)\n", argv[1], bfd_errmsg(bfd_get_error()));
        if (bfd_check_format(f, bfd_core)) {
          printf("--> core dump\n");
        } else if (bfd_check_format(f, bfd_archive)) {
          printf("--> archive\n");
        }
      }

      // bfd work around.
      bfd_set_error(bfd_error_no_error);

      if (bfd_get_flavour(f) == bfd_target_unknown_flavour) {
        printf("ERROR: unrecognized format for binary '%s' (%s)\n", argv[1], bfd_errmsg(bfd_get_error()));
      } else if (bfd_get_flavour(f) == bfd_target_msdos_flavour) {
        printf("--> msdos flavour\n");
      } else if (bfd_get_flavour(f) == bfd_target_coff_flavour) {
        printf("--> coff flavour\n");
      } else if (bfd_get_flavour(f) == bfd_target_elf_flavour) {
        printf("--> elf flavour\n");
      }

      bfd_close(f);
    } else {
      printf("ERROR: failed to open binary '%s' (%s)\n", argv[1], bfd_errmsg(bfd_get_error()));
    }
  }

  return 0;
}

