FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Cài đặt các thư viện cần thiết
RUN apt-get update && apt-get install -y \
    g++ \
    libmysqlcppconn-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy toàn bộ project vào container
COPY . .

# --- BẮT ĐẦU TỰ ĐỘNG SỬA CODE CHO LINUX ---

# 1. Sửa lỗi localtime_s (Windows) -> localtime_r (Linux)
RUN sed -i 's/localtime_s(&local_tm, &tt)/localtime_r(\&tt, \&local_tm)/g' RestaurantOrderManagement/RestaurantOrderManagement/Invoice.cpp && \
    sed -i 's/localtime_s(&local_tm, &tt)/localtime_r(\&tt, \&local_tm)/g' RestaurantOrderManagement/RestaurantOrderManagement/Order.cpp

# 2. Sửa lỗi trong MainMenu.cpp (cls -> clear, thêm _getch)
RUN sed -i 's/system("cls")/system("clear")/g' RestaurantOrderManagement/RestaurantOrderManagement/MainMenu.cpp && \
    sed -i '/#include "MainMenu.h"/a #include <termios.h>\n#include <unistd.h>\n#include <stdio.h>\n\nint _getch() {\n    struct termios oldt, newt;\n    int ch;\n    tcgetattr(STDIN_FILENO, &oldt);\n    newt = oldt;\n    newt.c_lflag &= ~(ICANON | ECHO);\n    tcsetattr(STDIN_FILENO, TCSANOW, &newt);\n    ch = getchar();\n    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);\n    return ch;\n}\n' RestaurantOrderManagement/RestaurantOrderManagement/MainMenu.cpp

# 3. Sửa lỗi Cashier.cpp: Thêm return {}
RUN sed -i '/std::cout << "Error viewing orders: " << e.what() << std::endl;/a \ \ \ \ \ \ \ \ return {};' RestaurantOrderManagement/RestaurantOrderManagement/Cashier.cpp

# 4. Sửa lỗi system("pause") trong Database.cpp
RUN sed -i 's/system("pause");//g' RestaurantOrderManagement/RestaurantOrderManagement/Database.cpp

# 5. Sửa lỗi thiếu thư viện <cstdlib>
RUN sed -i '/#include <unistd.h>/a #include <cstdlib>' RestaurantOrderManagement/RestaurantOrderManagement/get_cross.h

# 6. Sửa lỗi Circular Dependency giữa Invoice.h và Cashier.h
RUN sed -i 's/#include "Cashier.h"/class Cashier;/g' RestaurantOrderManagement/RestaurantOrderManagement/Invoice.h && \
    sed -i 's/Cashier cashier/const Cashier\& cashier/g' RestaurantOrderManagement/RestaurantOrderManagement/Invoice.h && \
    sed -i '/#include "Invoice.h"/a #include "Cashier.h"' RestaurantOrderManagement/RestaurantOrderManagement/Invoice.cpp && \
    sed -i 's/Cashier cashier/const Cashier\& cashier/g' RestaurantOrderManagement/RestaurantOrderManagement/Invoice.cpp

# 7. [QUAN TRỌNG] Fix lỗi thiếu thư viện Windows.h (Comment bỏ dòng include)
RUN sed -i 's/#include "Windows.h"/\/\/ #include "Windows.h"/g' RestaurantOrderManagement/RestaurantOrderManagement/common.h && \
    sed -i 's/#include "Windows.h"/\/\/ #include "Windows.h"/g' RestaurantOrderManagement/RestaurantOrderManagement/get_cross.h

# --- KẾT THÚC SỬA CODE ---

# Copy file config ra thư mục gốc để app tìm thấy
RUN mkdir -p config && \
    cp RestaurantOrderManagement/RestaurantOrderManagement/config/db_config.json config/

# Compile code
RUN g++ -std=c++17 \
    RestaurantOrderManagement/RestaurantOrderManagement/*.cpp \
    -IRestaurantOrderManagement/RestaurantOrderManagement/include \
    -lmysqlcppconn \
    -lssl -lcrypto \
    -o restaurant_app

CMD ["./restaurant_app"]