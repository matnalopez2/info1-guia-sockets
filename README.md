
## Ejercitación en clase - sockets

Realizar aplicaciones del tipo cliente-servidor, en donde el servidor se encuentre diseñado para funcionar en modo 
7x24. 
Salvo se indique algo diferente, el servidor quedará escuchando en el puerto 8008. En caso que este puerto este 
ocupado, seleccione uno que se encuentre disponible. 
Para simplificar las pruebas o debugging (depuración) de estas aplicaciones, vamos a trabajar en toda esta primera 
etapa con datos tipo ASCII o aplicaciones que trabajan en este modo.  
Como aplicación cliente, se utilizará inicialmente la aplicación telnet para lo cual deberá ejecutar: 

``` bash
telnet IP_address puerto 
```

Si estamos trabajando sobre la misma máquina esto se escribirá: 

``` bash
telnet localhost 8008 
```

### Ejercicio 1: 
Realizar una aplicación servidora que cada vez que reciba una conexión, responda con la fecha y hora actual 
y cierre la conexión. (El formato a utilizar para enviar los datos queda a criterio del programador) 

### Ejercicio 2: 
Realizar una aplicación servidora que cada vez que reciba una conexión, espere la recepción de un texto, 
responda con el mismo texto en forma invertida y cierre la conexión. 
En caso de no haber recibido un texto dentro de un determinado tiempo, por ejemplo 10 segundos, responda 
con un texto predefinido y cierre la conexión. 

### Ejercicio 3: 
Modificar el ejercicio anterior para que: - 
La aplicación servidora sea concurrente. Es decir, permita mantener dialogo con varios clientes a la vez.
Permita al cliente enviar más de una cadena de texto y responder a cada una de ellas con el mismo texto 
en forma invertida. 
Se cierre la conexión al recibir el texto “Chau” o pase un determinado tiempo sin recibir ningún mensaje. 
Previo al cierre de la conexión, se debe enviar al cliente un texto alusivo al motivo del cierre. 

### Ejercicio 4: 
Agregar al servidor anterior, la posibilidad de responder a ciertas consultas (por ejemplo la fecha, la hora, etc.) 
en todos los otros caso se debe mantener el comportamiento definido en el punto 3. 
Queda a criterio del desarrollador el formato de estos mensajes.


---

## Tutorial para trabajar mediante GitHub

### Forkear el repositorio para trabajar

Para empezar, tienen que hacer un fork del proyecto para que tengan todo y puedan comenzar a trabajar en su propio repositorio.
Para esto, deben hacer click en el botón fork de este repositorio. Una vez realizado, deben clonar el repositorio en su máquina local:

``` bash
git clone [URL_de_su_repositorio]
``` 

### Editar y resolver el ejercicio

Una vez que tengan los archivos en su máquina, deben crear una rama para resolver el enunciado.

``` bash
git checkout -b [NOMBRE_DE_LA_RAMA]
``` 

### Pushear los cambios

Para enviar los cambios, necesitan seguir los pasos típicos:

``` bash
git add .
git commit -m "MENSAJE"
git push origin [NOMBRE_DE_LA_RAMA]
``` 

### Crear Pull Request

Desde github.com hagan click en "Compare and Pull Request" para crear el PR.