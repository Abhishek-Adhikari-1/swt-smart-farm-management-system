FROM gcc:latest

WORKDIR /FINAL_PROJECT

COPY . .

RUN gcc -o main main.c

CMD ["./main"]
