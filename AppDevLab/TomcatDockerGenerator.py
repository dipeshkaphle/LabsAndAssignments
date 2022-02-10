dockerfile='''FROM tomcat:9.0.0
EXPOSE 8080
CMD ["catalina.sh", "run"]
'''

compose='''
version: '3'
services:
  tomcat_server: 
    build: .
    ports:
      - "8080:8080" # local:container
    volumes:
      - ./target:/usr/local/tomcat/webapps
    restart: always
    
'''
open('Dockerfile','w').write(dockerfile)
open('docker-compose.yml','w').write(compose)
