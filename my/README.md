# Command

```sh
docker compose build [--pull] [--no-cache]

docker compose run --rm gtest make clean
docker compose run --rm gtest make q04_01
docker compose run --rm gtest make -j4
docker compose run --rm gtest make testall
```

```sh
# Arch Linux
docker compose run --rm gtest make 23 -j4
docker compose run --rm gtest make 23testall
docker compose run --rm gtest make 23clean

# Mac
make 2b -j4
make 2btestall
make 2bclean
```

# ToDo
- [ ] Boost Graph
