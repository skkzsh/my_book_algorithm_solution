```bash
docker compose build [--pull] [--no-cache]
docker compose run --rm gtest make clean
docker compose run --rm gtest make q04_01
docker compose run --rm gtest make -j4
docker compose run --rm gtest make testall
```
