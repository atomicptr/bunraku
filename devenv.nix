{ pkgs, ... }:

{
  packages = with pkgs; [
    llvmPackages_19.clang-tools
    cmake
    just

    xorg.libX11
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXcursor
    xorg.libXi
    libglvnd

    gcc14
  ];
}
