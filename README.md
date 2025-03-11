# build
```bash
mkdir build
cmake -S . -B build
```
# run
```bash
cmake --build build
```
# clean
```bash
cmake --build build --target clean
```
# test
```bash
echo "{\"method\":\"sayHello\"}" | nc localhost 1234
or
echo "{\"method\": \"add\", \"params\": [3,4], \"id\": \"SOME_IDENTIFIER\" }" | nc  localhost 1234
or
echo "{\"method\":\"exit\"}" | nc localhost 1234
```

