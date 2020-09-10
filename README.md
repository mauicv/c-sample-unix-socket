## Sample C Unix server

___

Simple program that opens a unix socket and outputs to stdout any message sent from the client.

To close the the server send quit from the client: `./client quit`.
___

To build:

```sh
make server
make client
```

___

To clean:

```sh
make clean
```
