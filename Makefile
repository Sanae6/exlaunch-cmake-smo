# todo FTP_IP and LOGGER_IP flags

.PHONY: all clean

all:
	cmake --toolchain=cmake/toolchain.cmake -S . -B build && $(MAKE) -C build

clean:
	rm -r build || true
