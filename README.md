# ivmone

[![readme style standard badge]][standard readme]
[![appveyor badge]][appveyor]
[![license badge]][Apache License, Version 2.0]

> Fast ILCOIN Virtual Machine implementation

_ivmone_ is a C++ implementation of the ILCOIN Virtual Machine (IVM).
Created by members of the [Ewasm] team, the project aims for clean, standalone IVM implementation
that can be imported as an execution module by ILCOIN Client projects.
The codebase of _ivmone_ is optimized to provide fast and efficient execution of IVM smart contracts.

### Characteristic of ivmone

1. Exposes the [IVMC] API.
2. Requires C++17 standard.
3. The [intx] library is used to provide 256-bit integer precision.
4. The [ethash] library is used to provide Keccak hash function implementation
   needed for the special `KECCAK256` instruction.
5. Contains two interpreters: **Advanced** (default) and **Baseline** (experimental).

### Advanced Interpreter

1. The _indirect call threading_ is the dispatch method used -
   a loaded IVM program is a table with pointers to functions implementing virtual instructions.
2. The gas cost and stack requirements of block of instructions is precomputed
   and applied once per block during execution.
3. Performs extensive and expensive bytecode analysis before execution.

### Baseline Interpreter

1. Provides relatively straight-forward IVM implementation.
2. Performs only minimalistic `JUMPDEST` analysis.
3. Experimental. Can be enabled with `O=0` option.


## Usage

### Optimization levels

The option `O` controls the "optimization level":
- `O=2` uses Advanced interpreter (default),
- `O=0` uses Baseline interpreter.

### As geth plugin

ivmone implements the [IVMC] API for ILCOIN Virtual Machines.
It can be used as a plugin replacing geth's internal IVM. But for that a modified
version of geth is needed. The [Ewasm]'s fork
of go-ethereum provides [binary releases of geth with IVMC support](https://github.com/ewasm/go-ethereum/releases).

Next, download ivmone from [Releases].

Start the downloaded geth with `--vm.ivm` option pointing to the ivmone shared library.

```bash
geth --vm.ivm=./libivmone.so
```

### Building from source
To build the ivmone IVMC module (shared library), test, and benchmark:

1. Fetch the source code:
   ```
   git clone --recursive https://github.com/ILCOINDevelopmentTeam/ivmone
   cd ivmone
   ```

2. Configure the project build and dependencies:
   ##### Linux / OSX
   ```
   cmake -S . -B build -DIVMONE_TESTING=ON
   ```

   ##### Windows
   *Note: >= Visual Studio 2019 is required since ivmone makes heavy use of C++17*
   ```
   cmake -S . -B build -DIVMONE_TESTING=ON -G "Visual Studio 16 2019" -A x64
   ```

3. Build:
   ```
   cmake --build build --parallel
   ```


3. Run the unit tests or benchmarking tool:
   ```
   build/bin/ivmone-unittests
   build/bin/ivmone-bench test/benchmarks
   ```
### Tools

#### ivm-test

The **ivm-test** executes a collection of unit tests on
any IVMC-compatible ILCOIN Virtual Machine implementation.
The collection of tests comes from the ivmone project.

```bash
ivm-test ./ivmone.so
```

### Docker

Docker images with ivmone are available on Docker Hub:
https://hub.docker.com/r/ILCOINDevelopmentTeam/ivmone.

Having the ivmone shared library inside a docker is not very useful on its own,
but the image can be used as the base of another one or you can run benchmarks
with it.

```bash
docker run --entrypoint ivmone-bench ILCOINDevelopmentTeam/ivmone /src/test/benchmarks
```

## References

1. IVM is gas free.

## Maintainer

Paweł Bylica [@chfast]

## License

[![license badge]][Apache License, Version 2.0]

Licensed under the [Apache License, Version 2.0].


[@chfast]: https://github.com/chfast
[appveyor]: https://ci.appveyor.com/project/chfast/ivmone/branch/master
[Apache License, Version 2.0]: LICENSE
[ILCOIN]: https://ilcoincrypto.com/
[IVMC]: https://github.com/ILCOINDevelopmentTeam/ivmc
[Ewasm]: https://github.com/ewasm
[intx]: https://github.com/chfast/intx
[ethash]: https://github.com/chfast/ethash
[Releases]: https://github.com/ILCOINDevelopmentTeam/ivmone/releases
[standard readme]: https://github.com/RichardLitt/standard-readme

[appveyor badge]: https://img.shields.io/appveyor/ci/chfast/ivmone/master.svg?logo=appveyor
[license badge]: https://img.shields.io/github/license/ethereum/ivmone.svg?logo=apach
[readme style standard badge]: https://img.shields.io/badge/readme%20style-standard-brightgreen.svg
