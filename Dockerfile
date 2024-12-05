FROM ubuntu

RUN apt update && apt upgrade -y && apt install make git libreadline -y

RUN git clone https://github.com/anonymousc/merged-minshell.git minishell 

# VOLUME [ "~/." ]


RUN cd minishell && git checkout parser && make && ./minishell