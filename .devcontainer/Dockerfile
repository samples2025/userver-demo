FROM ubuntu:22.04

ARG USERNAME=builder
ARG UID=1000
ARG GID=${UID}

ARG USERVER_SRC="/userver-src"
ARG DEBIAN_FRONTEND=noninteractive

ENV TZ=Europe/Moscow

RUN \
	set -eu; \
	mkdir ${USERVER_SRC}; \
	apt-get update; \
	apt-get dist-upgrade -y; \
	groupadd -g ${GID} ${USERNAME}; \
	useradd -u ${UID} -g ${GID} -s /bin/bash -m ${USERNAME}; \
	apt-get install -y --no-install-recommends \
		ca-certificates \
		git; \
	git clone --depth 1 https://github.com/userver-framework/userver.git "${USERVER_SRC}"; \
	apt install --allow-downgrades -y $(cat "${USERVER_SRC}/scripts/docs/en/deps/ubuntu-22.04.md" | tr "\n" " "); \
	apt-get install -y --no-install-recommends \
		clang-format; \
	rm -rf /var/lib/apt/lists/*; \
	cd ${USERVER_SRC}; \
	cmake \
		-S./ \
		-B./build \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_C_COMPILER=clang-14 \
		-DCMAKE_CXX_COMPILER=clang++-14 \
		-DUSERVER_FEATURE_STACK_USAGE_MONITOR=OFF \
		-DUSERVER_INSTALL=ON \
		-DUSERVER_SANITIZE="ub addr" \
		-GNinja; \
	cmake --build build/; \
	cmake --install build/; \
	rm -rf ${USERVER_SRC}

USER ${USERNAME}
