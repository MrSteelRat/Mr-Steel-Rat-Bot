# Use the official Alpine Linux as a base image
FROM alpine:latest AS builder

# Set the working directory for dependencies
WORKDIR /app/deps

# Install build dependencies
RUN apk --no-cache add \
    g++ \
    make \
    binutils \
    cmake \
    boost-dev \
    openssl-dev \
    zlib-dev \
    libcurl \
    git \
    ccache \
    sqlite-dev \
    ninja

# Clone and build tgbot-cpp
RUN if [ ! -d "tgbot-cpp" ]; then \
    git clone https://github.com/reo7sp/tgbot-cpp && \
    cd tgbot-cpp && \
    cmake -GNinja . && \
    ninja && \
    ninja install && \
    cd /app; \
fi

# Set the working directory for the application code
WORKDIR /app

# Copy application source code
COPY CMakeLists.txt ./
COPY src/ ./src/
COPY module/ ./module/

# Build your application
RUN cmake -GNinja -Bbuild && ninja -C build

# Final image
FROM alpine:latest

# Set the working directory
WORKDIR /app

# Install runtime dependencies
RUN apk --no-cache add \
    boost \
    openssl \
    zlib \
    libcurl \
    sqlite-libs

# Copy only the necessary artifacts from the builder stage
COPY --from=builder /app/build /app/build
COPY --from=builder /usr/local/include /usr/local/include
COPY --from=builder /usr/local/lib /usr/local/lib

# Copy shared libraries to the same directory as the executable
RUN cp /usr/local/lib/* /app/build/

# Clean up unnecessary dependencies
RUN apk --no-cache del \
    g++ \
    make \
    binutils \
    cmake \
    git \
    ccache \
    ninja

# Set your application entry point
CMD ["./build/telegram_bot"]

