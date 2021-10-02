docker run -ti  --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" -v "$PWD":/programs ns2
