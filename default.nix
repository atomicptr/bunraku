let
  pkgs = import <nixpkgs> { };
in
pkgs.mkShell {
  packages = with pkgs; [
    gcc14
    llvmPackages_19.clang-tools
  ];

  buildInputs = with pkgs; [
      raylib
  ];
}
