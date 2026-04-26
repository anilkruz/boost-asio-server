# Boost.Asio Async TCP Server — C++

High performance async TCP server using Boost.Asio.
Handles 10,000 concurrent clients on a single thread.

## Benchmark Results
- 10,000 clients simultaneously
- 122,514 requests/second
- Single thread — async callbacks
- 2x faster than raw epoll server

## Files
- `hello_asio.cc`    — io_context basics
- `timer.cc`         — async timer
- `server.cc`        — blocking server (learning)
- `async_server.cc`  — production async server

## Concepts
- io_context = epoll internally
- async_accept → async_read → async_write
- shared_ptr for socket lifetime
- Recursive callback chain
- Lambda capture for context

## Build
```bash
g++ -std=c++20 -o async_server async_server.cc
g++ -std=c++20 -o stress_client stress_client.cc -lpthread
```

## Run
```bash
# Terminal 1
./async_server

# Terminal 2 — stress test
./stress_client
```

## Comparison
| Server | Clients | Req/sec |
|--------|---------|---------|
| Raw TCP epoll | 10,000 | 61,000 |
| Boost.Asio async | 10,000 | 122,514 |
