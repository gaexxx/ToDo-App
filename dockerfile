# ===== Build stage =====
FROM ubuntu:24.04 AS build

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    qmake6 \
    qt6-base-dev \
    qt6-base-dev-tools \
    qt6-svg-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN qmake6 mytodo.pro CONFIG+=release && \
    make -j"$(nproc)"


# ===== Runtime stage =====
FROM ubuntu:24.04 AS runtime

ENV DEBIAN_FRONTEND=noninteractive
ENV QT_QPA_PLATFORM=xcb
ENV QT_X11_NO_MITSHM=1

RUN apt-get update && apt-get install -y --no-install-recommends \
    libqt6widgets6t64 \
    libqt6svg6 \
    libxcb-cursor0 \
    libxkbcommon-x11-0 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

COPY --from=build /app/My-ToDo /usr/local/bin/mytodo

RUN useradd -m appuser
USER appuser

CMD ["/usr/local/bin/mytodo"]