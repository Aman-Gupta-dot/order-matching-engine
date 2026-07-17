FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y \
    g++ \
    make \
    libasio-dev

WORKDIR /app

COPY . .

RUN g++ \
backend/main.cpp \
backend/ApiServer.cpp \
engine/src/CustomLinkedQueue.cpp \
engine/src/Exchange.cpp \
engine/src/ExchangeStatistics.cpp \
engine/src/menu.cpp \
engine/src/Node.cpp \
engine/src/OrderBook.cpp \
engine/src/VerifyIntegrity.cpp \
engine/tests/stressTest.cpp \
-IBackendServerFiles/Crow/include \
-Iengine/include \
-std=c++17 \
-o server

CMD ["./server"]