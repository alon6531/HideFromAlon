FROM ubuntu:22.04
RUN apt-get update && apt-get install -y build-essential cmake ca-certificates curl
WORKDIR /app
COPY CMakeLists.txt .
COPY src/ ./src/
RUN cmake -B build && cmake --build build --target Server
EXPOSE 9000/udp
CMD ["./build/Server"]