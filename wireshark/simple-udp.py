import socket
import struct
import time

try:
  # Create socket
  sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

  # Prepare and send datagrams until interrupted
  counter = 0
  payload_bytes = "The quick brown fox jumped over the lazy dog".encode()
  print("Sending frames...")
  while True:
    # Pack new datagram, relying on struct.pack to truncate counter to the required size each time
    datagram = struct.pack("<QBHL", int(time.time() * 1000), counter % 256, counter % 65536, counter % 4294967296) + payload_bytes

    # Send datagram to localhost on port 65432
    sock.sendto(datagram, ("127.0.0.1", 65432))

    # Increment counter
    counter += 1

    # Nap time
    time.sleep(0.01)

except KeyboardInterrupt:
    pass
