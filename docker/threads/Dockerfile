FROM docker.io/fedora:30
MAINTAINER Grzegorz Grzybek <gr.grzybek@gmail.com>
RUN dnf install -y tar telnet unzip which wget procps-ng iproute net-tools && dnf clean all -y
RUN mkdir /work
WORKDIR /work
COPY threads /work
CMD /work/threads
