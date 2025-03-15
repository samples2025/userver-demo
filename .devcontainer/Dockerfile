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
		git \
		vim; \
	git clone --depth 1 https://github.com/userver-framework/userver.git "${USERVER_SRC}"; \
	apt install --allow-downgrades -y $(cat "${USERVER_SRC}/scripts/docs/en/deps/ubuntu-22.04.md" | tr "\n" " "); \
	rm -rf /var/lib/apt/lists/*; \
	cd ${USERVER_SRC}; \
	cmake \
		-S./ \
		-B./build_release \
		-DCMAKE_BUILD_TYPE=Release \
		-DUSERVER_INSTALL=ON \
		-GNinja; \
	cmake --build build_release/; \
	cmake --install build_release/; \
	rm -rf ${USERVER_SRC}

USER ${USERNAME}
