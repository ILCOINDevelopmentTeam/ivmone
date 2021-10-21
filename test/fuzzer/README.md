# ivmone-fuzzer

> [LibFuzzer] powered testing tool for [IVMC]-compatible EVM implementations.

## License

The ivmone-fuzzer source code is licensed under the [Apache License, Version 2.0].

### Exceptions

Depending on build system options selected, 
the [aleth-interpreter][Aleth] is statically _linked to_ the ivmone-fuzzer executable.
The [Aleth] project is licensed under [GNU General Public License, Version 3] therefore 
the final ivmone-fuzzer binary is also licensed under [GNU General Public License, Version 3].

[Aleth]: https://github.com/ethereum/aleth
[Apache License, Version 2.0]: https://www.apache.org/licenses/LICENSE-2.0.txt
[IVMC]: https://github.com/ILCOINDevelopmentTeam/ivmc
[ivmone]: https://github.com/ethereum/ivmone
[GNU General Public License, Version 3]: LICENSE
[LibFuzzer]: https://llvm.org/docs/LibFuzzer.html
