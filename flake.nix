{
  description = "Dev Env";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-21.11";
    flake-utils.url =
      "github:numtide/flake-utils/3cecb5b042f7f209c56ffd8371b2711a290ec797";
    rust-overlay.url =
      "github:oxalica/rust-overlay/2af4f775282ff9cb458c3ef6f30c0a8f689d202b";
    rust-overlay.inputs.nixpkgs.follows = "nixpkgs";
    rust-overlay.inputs.flake-utils.follows = "flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils, rust-overlay, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        overlays = [ (import rust-overlay) ];
        pkgs = import nixpkgs { inherit system overlays; };
      in rec {
        package.update = pkgs.writeShellApplication {
          name = "update";
          runtimeInputs = [ pkgs.git pkgs.rust-bindgen pkgs.rustfmt ];
          text = ''
            git submodule update
            generate() {
                echo "Generating bindings for $1"
                bindgen \
                    lib/src/uefi.h \
                    --use-core \
                    --with-derive-default \
                    --with-derive-eq \
                    --with-derive-hash \
                    --with-derive-ord \
                    --rustified-enum "*" \
            	      --blocklist-type "MEMORY_ERROR_CORRECT_CAPABILITY" \
                    --blocklist-type "EFI_KEY_OPTION" \
                    --ctypes-prefix crate::ctypes \
            	      --rust-target nightly \
                    -- -I lib/extra/edk2/MdePkg/Include/ \
                    -I lib/extra/edk2/MdePkg/Include/"$1"/ \
                    -I lib/extra/edk2/MdePkg/Include/Library/ \
                    -I lib/extra/edk2/MdeModulePkg/Include/ \
                    -I lib/extra/edk2/NetworkPkg/ \
                    -I lib/extra/edk2/NetworkPkg/Include/ \
                    -I lib/extra/edk2/RedfishPkg/Include/ \
                    -I lib/extra/edk2/RedfishPkg/ \
                    --target=x86_64-unknown-uefi \
                    -nostdlib -fshort-wchar | sed 's/MEMORY_ERROR_CORRECT_CAPABILITY/crate\:\:MEMORY_ERROR_CORRECT_CAPABILITY/g' > lib/src/bindings_"$1".rs
            }
            bindgen --version
            generate "X64"
            generate "Arm"
            generate "AArch64"
            generate "Ia32"
          '';
        };
        defaultPackage = package.update;
        devShell = pkgs.mkShell {
          buildInputs = [
            package.update
            pkgs.clang_13
            (pkgs.rust-bin.selectLatestNightlyWith (toolchain:
              toolchain.default.override { extensions = [ "rust-src" ]; }))
          ];
          LD_LIBRARY_PATH = "$LD_LIBRARY_PATH:${pkgs.stdenv.cc.cc.lib}/lib";
        };
      });
}

