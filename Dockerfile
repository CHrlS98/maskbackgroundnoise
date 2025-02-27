FROM ubuntu:24.04

WORKDIR /
COPY . /maskbackgroundnoise

RUN apt update && apt install -y build-essential

WORKDIR /maskbackgroundnoise
RUN make
ENV PATH="${PATH}:/maskbackgroundnoise/bin/x86_64-pc-linux-gnu"

WORKDIR /maskbackgroundnoise/bin/x86_64-pc-linux-gnu
RUN mv maskbackgroundnoise25a_x86_64-pc-linux-gnu maskbackgroundnoise

WORKDIR /
