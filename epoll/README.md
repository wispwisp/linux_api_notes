# epoll

`bash create_container.sh && bash run_container.sh`

`mkdir build && cd build`

`cmake ../ && make && ./server/server 8080`

---

`docker exec -it linux_api_notes_epoll /bin/bash`

`cd build`

`./load_tests/tester 8080`
