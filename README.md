# My-ToDo
Progetto programmazione ad oggetti

## Istruzioni
Per compilare nel container Docker:

```bash
# Solo una volta
xhost +local:docker

docker run --rm -it \
  -e DISPLAY="$DISPLAY" \
  -e QT_X11_NO_MITSHM=1 \
  -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
  mytodo
  ```

`/usr/lib/qt6/bin/qmake`  
`make`

Per eseguire l'applicazione:
```bash
./My-ToDo
```