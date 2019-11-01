1. jffs2 Usage：
Options:
  -p, --pad[=SIZE]        Pad output to SIZE bytes with 0xFF. If SIZE is
                          not specified, the output is padded to the end of
                          the final erase block
  -r, -d, --root=DIR      Build file system from directory DIR (default: cwd)
  -s, --pagesize=SIZE     Use page size (max data node size) SIZE (default: 4KiB)
  -e, --eraseblock=SIZE   Use erase block size SIZE (default: 64KiB)
  -c, --cleanmarker=SIZE  Size of cleanmarker (default 12)
  -m, --compr-mode=MODE   Select compression mode (default: priortiry)
  -x, --disable-compressor=COMPRESSOR_NAME
                          Disable a compressor
  -X, --enable-compressor=COMPRESSOR_NAME
                          Enable a compressor
  -y, --compressor-priority=PRIORITY:COMPRESSOR_NAME
                          Set the priority of a compressor
  -L, --list-compressors  Show the list of the avaiable compressors
  -t, --test-compression  Call decompress and compare with the original (for test)
  -n, --no-cleanmarkers   Don't add a cleanmarker to every eraseblock
  指明不添加清楚标记（nand flash 有自己的校检块，存放相关的信息。）
  如果挂载后会出现类似：CLEANMARKER node found at 0x0042c000；  has totlen 0xc != normal 0x0 的警告，则加上-n 就会消失。
  -o, --output=FILE       Output to FILE (default: stdout)
  -l, --little-endian     Create a little-endian filesystem
  -b, --big-endian        Create a big-endian filesystem
  -D, --devtable=FILE     Use the named FILE as a device table file
  -f, --faketime          Change all file times to '0' for regression testing
  -q, --squash            Squash permissions and owners making all files be owned by root
  -U, --squash-uids       Squash owners making all files be owned by root
  -P, --squash-perms      Squash permissions on all files
  -h, --help              Display this help text
  -v, --verbose           Verbose operation
  -V, --version           Display version information
  -i, --incremental=FILE  Parse FILE and generate appendage output for it
2. sample
mkfs.jffs2 --eraseblock=0x10000 -l -n --pad=0x100000 -d ./factory -o ./config.img
/* 指定了大小--pad=0x60000，若数据不够则使用0xFF补充 */
mkfs.jffs2 --eraseblock=0x10000 -l -n  -d ./app/factory -o ./config.img
/* 输出文件是实际的大小，默认使用了zlib压缩 */
mkfs.jffs2  -L  /* 列出支持的压缩格式 */
mkfs.jffs2:
      zlib priority:60 enabled
     rtime priority:50 enabled
