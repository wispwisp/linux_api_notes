#!/bin/bash

docker run -it --rm -v $(pwd -P)/proj:/src \
       --name=linux_api_notes_epoll linux_api_notes/epoll
