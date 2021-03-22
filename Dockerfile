# Serves React Bot static files
FROM nginx:alpine

# Installs bash in alpine image to allow the use of bash (useful for debugging the container)
RUN apk update && apk add bash

RUN mkdir /home/tcc
WORKDIR /home/tcc

COPY . /home/tcc
COPY ./default.conf /etc/nginx/conf.d
RUN mv /home/tcc/build/* /usr/share/nginx/html
EXPOSE 80/tcp
CMD ["nginx", "-g", "daemon off;"]
