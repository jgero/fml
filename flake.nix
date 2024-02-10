{
  description = "Funky Markup Language";
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
  };
  outputs = { self, nixpkgs }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
  in {
    packages.${system}.default = pkgs.stdenv.mkDerivation rec {
      name = "fml";
      pname = name;
      version = "0.1";
      src = ./compiler;
      buildInputs = with pkgs; [
        gcc
        flex
        bison
      ];
      buildPhase = ''
         mkdir -p $out/bin
         pushd parser
         bison -d parser.y
         popd
         pushd scanner
         flex scanner.l
         popd
         g++ main.cpp -o fml -lm -std=c++11
         mv fml $out/bin/
      '';
    };
    devShells.${system}.default = pkgs.mkShell {
      packages = with pkgs; [
        clang-tools
        flex
        bison
      ];
    };
  };
}
