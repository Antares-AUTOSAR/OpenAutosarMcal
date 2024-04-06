FROM jenkins/jenkins:lts

USER root

RUN apt-get update && apt-get install -y \
    curl \
    git \
    nano

RUN cat /var/jenkins_home/secrets/initialAdminPassword
