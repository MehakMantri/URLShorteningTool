{ pkgs }: {
  deps = [
    pkgs.clang_12
    pkgs.ccls
    pkgs.gdb
    pkgs.gnumake
    pkgs.sqlite
    pkgs.curl
    pkgs.nlohmann_json
    
  ];
}
