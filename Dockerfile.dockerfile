FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    g++ \
    libmysqlcppconn-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy toàn bộ project
COPY . .

# Compile
RUN g++ -std=c++17 \
    RestaurantOrderManagement/RestaurantOrderManagement/*.cpp \
    -IRestaurantOrderManagement/RestaurantOrderManagement/include \
    -lmysqlcppconn \
    -lssl -lcrypto \
    -o restaurant_app

CMD ["./restaurant_app"]
