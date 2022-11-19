xhost +local:root
docker run --rm -it \
  --user root \
  --name 'cpp_practice' \
  --env="DISPLAY" \
  --volume=/home/gskim/Documents/practices/cpp20-modules:/src \
  ubuntu22-gcc11:giseopkim \
  /bin/bash -c 'cd /src; bash'
