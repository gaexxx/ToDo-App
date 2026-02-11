# My-ToDo
Progetto programmazione ad oggetti

## Istruzioni
Per compilare nel container Docker:

```bash
# Solo una volta
xhost +local:docker

docker run -it --rm \
  -v "$(pwd)":/app -w /app \
  -u $(id -u):$(id -g) \
  -e DISPLAY=$DISPLAY \
  -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
  -v $XDG_RUNTIME_DIR:$XDG_RUNTIME_DIR \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  unipd-oop/qt-env:2025 bash
  ```

`/usr/lib/qt6/bin/qmake`  
`make`

Per eseguire l'applicazione:
```bash
./My-ToDo
```