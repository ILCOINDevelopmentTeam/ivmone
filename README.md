# ivmone

[![ethereum badge]][ethereum]
[![readme style standard badge]][standard readme]
[![codecov badge]][codecov]
[![circleci badge]][circleci]
[![appveyor badge]][appveyor]
[![license badge]][Apache License, Version 2.0]

> Fast Ethereum Virtual Machine implementation

_ivmone_ is a C++ implementation of the Ethereum Virtual Machine (EVM). 
Created by members of the [Ewasm] team, the project aims for clean, standalone EVM implementation 
that can be imported as an execution module by Ethereum Client projects. 
The codebase of _ivmone_ is optimized to provide fast and efficient execution of EVM smart contracts.

### Characteristic of ivmone

1. Exposes the [IVMC] API.
2. Requires C++17 standard.
3. The [intx] library is used to provide 256-bit integer precision.
4. The [ethash] library is used to provide Keccak hash function implementation
   needed for the special `KECCAK256` instruction.
5. Contains two interpreters: **Advanced** (default) and **Baseline** (experimental).
   
### Advanced Interpreter

1. The _indirect call threading_ is the dispatch method used -
   a loaded EVM program is a table with pointers to functions implementing virtual instructions.
2. The gas cost and stack requirements of block of instructions is precomputed 
   and applied once per block during execution.
3. Performs extensive and expensive bytecode analysis before execution.

### Baseline Interpreter

1. Provides relatively straight-forward EVM implementation.
2. Performs only minimalistic `JUMPDEST` analysis.
3. Experimental. Can be enabled with `O=0` option.


## Usage

### Optimization levels

The option `O` controls the "optimization level":
- `O=2` uses Advanced interpreter (default),
- `O=0` uses Baseline interpreter.

### As geth plugin

ivmone implements the [IVMC] API for Ethereum Virtual Machines.
It can be used as a plugin replacing geth's internal EVM. But for that a modified
version of geth is needed. The [Ewasm]'s fork
of go-ethereum provides [binary releases of geth with IVMC support](https://github.com/ewasm/go-ethereum/releases).

Next, download ivmone from [Releases].

Start the downloaded geth with `--vm.evm` option pointing to the ivmone shared library.

```bash
geth --vm.evm=./libivmone.so
```

### Building from source
To build the ivmone IVMC module (shared library), test, and benchmark:

1. Fetch the source code:
   ```
   git clone --recursive https://github.com/ethereum/ivmone
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

#### evm-test

The **evm-test** executes a collection of unit tests on 
any IVMC-compatible Ethereum Virtual Machine implementation.
The collection of tests comes from the ivmone project.

```bash
evm-test ./ivmone.so
```

### Docker

Docker images with ivmone are available on Docker Hub:
https://hub.docker.com/r/ethereum/ivmone.

Having the ivmone shared library inside a docker is not very useful on its own,
but the image can be used as the base of another one or you can run benchmarks 
with it.

```bash
docker run --entrypoint ivmone-bench ethereum/ivmone /src/test/benchmarks
```

## References

1. [Efficient gas calculation algorithm for EVM](docs/efficient_gas_calculation_algorithm.md)

## Maintainer

Paweł Bylica [@chfast]

## License

[![license badge]][Apache License, Version 2.0]

Licensed under the [Apache License, Version 2.0].


[@chfast]: https://github.com/chfast
[appveyor]: https://ci.appveyor.com/project/chfast/ivmone/branch/master
[circleci]: https://circleci.com/gh/ethereum/ivmone/tree/master
[codecov]: https://codecov.io/gh/ethereum/ivmone/
[Apache License, Version 2.0]: LICENSE
[ethereum]: https://ethereum.org
[IVMC]: https://github.com/ILCOINDevelopmentTeam/ivmc
[Ewasm]: https://github.com/ewasm
[intx]: https://github.com/chfast/intx
[ethash]: https://github.com/chfast/ethash
[Releases]: https://github.com/ethereum/ivmone/releases
[standard readme]: https://github.com/RichardLitt/standard-readme

[appveyor badge]: https://img.shields.io/appveyor/ci/chfast/ivmone/master.svg?logo=appveyor
[circleci badge]: https://img.shields.io/circleci/project/github/ethereum/ivmone/master.svg?logo=circleci
[codecov badge]: https://img.shields.io/codecov/c/github/ethereum/ivmone.svg?logo=codecov
[ethereum badge]: https://img.shields.io/badge/ethereum-EVM-informational.svg?logo=ethereum
[license badge]: https://img.shields.io/github/license/ethereum/ivmone.svg?logo=apache
[readme style standard badge]: https://img.shields.io/badge/readme%20style-standard-brightgreen.svg
