FROM eclipse-temurin:21.0.2_13-jdk
WORKDIR /rccarapp

COPY mvnw .
COPY mvnw.cmd .
COPY .mvn .mvn
COPY pom.xml .
COPY src src
RUN ./mvnw clean package
RUN apt-get update && \
    apt-get install -y bluez libbluetooth3-dev python3 \
RUN pip install pyserial
# RUN ./mvnw package

#COPY ./target/*.jar app.jar
ENTRYPOINT ["java", "-jar", "./target/app-v1.jar"]