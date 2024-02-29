FROM eclipse-temurin:21.0.2_13-jdk
WORKDIR /rccarapp

COPY mvnw .
COPY mvnw.cmd .
COPY .mvn .mvn
COPY pom.xml .
COPY src src
RUN ./mvnw clean package
# RUN ./mvnw package

#COPY ./target/*.jar app.jar
ENTRYPOINT ["java", "-jar", "./target/app-v1.jar"]