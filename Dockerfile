# Use Ubuntu as base image
FROM ubuntu:22.04

# Install dev tools and libraries
RUN apt-get update && apt-get install -y \
  gcc \
  gdb \
  make \
  curl \
  git \
  libcurl4-openssl-dev \
  libcjson-dev \
  vim \
  build-essential \ 
  ca-certificates \
  openssh-client

ARG GIT_USERNAME
ARG GIT_TOKEN

RUN git config --global usr.name "$GIT_USERNAME" && \
    git config --global user.password "$GIT_TOKEN"

WORKDIR /app

CMD [ "bash" ]