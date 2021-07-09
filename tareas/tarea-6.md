# Medidas de Seguridad en los Sistemas Operativos

## Introducción

El desarrollo de sistemas computacionales es un tema complejo con muchas aristas
y ópticas aplicables. Si bien, el diseño, desarrollo e implementación de un
sistema de información conlleva sus retos, el asegurar y garantizar la seguridad
de su funcionamiento requiere de un esfuerzo especial en cada punto del proceso
así como de conocimientos de las herramientas que se pueden emplear para prevenir
y actuar frente a las amenazas en ciber-seguridad latentes en nuestro mundo
digital de hoy en día.

## Desarrollo

Limitando nuestro análisis al área de los Sistemas Operativos, lo primero que 
se puede observar es que cada uno puede realizar las labores de prevención y 
corrección de vulnerabilidades de formas distintas, pero con el mismo objetivo.
A continuación se analizarán los sistemas operativos más relevantes hoy en día
y se hablará sobre algunos de los elementos de seguridad que incorporan para
protegerse de algunos posibles vectores de ataque.

Uno de los primeros sistemas operativos que incluyeron medidas eficaces para 
prevenir distintos ataques fue UNIX. Lo primero que se implementó fue un robusto
sistema de permisos para escritura, lectura, ejecución. Posteriormente se
incluyeron usuarios y grupos de usuarios, pudiendo así gestionar más eficientemente
el acceso a cada archivo. Para prevenir operaciones indeseadas, se incluyó al
usuario "root", el cual tiene permiso de realizar cualquier acción, previniendo
así que los usuarios "normales" puedan realizar accioens inapropiadas. UNIX
incorpora, también, el uso de contraseñas para varios planos de control de
propiedades y configuraciones, así como para acceder al usuario "root". Pero,
y a pesar de que estas herramientas previenen una gran cantidad de ataques, el
fuerte del sistema operativo yace en su capacidad de actualización permanente
y constante, pudiendo así actualizar módulos de software independientemente
de otros permitiendo a los desarrolladores generar "parches" de seguridad y 
distribuirlos de forma eficiente.

En el caso de Linux, se conservan muchos elementos de seguridad provenientes
de UNIX como lo son los permisos, los usuarios, grupos de usuarios, el usuario
root, contraseñas y software fácilmente distribuíble y actualizable. Linux, a
su vez, implementa varios mecanismos de verificación de integridad mediante
sumas de comprobación MD5 y SHA-256/512/1024 con lo que se añade una capa de 
seguridad a la distribución de software. Otro elemento de seguridad es la suite
de herramientas GPG con la cual se pueden firmar digitalmente distintos archivos
y binarios permitiendo al usuario validar la identidad del autor y poder prevenir
ataques de modificaciones intermedias de contenido.

Microsoft Windows es, históricamente, la plataforma más vulnerada a lo largo
de los años. Esto, sin embargo, no tiene que ver con los mecanismos de protección
que incorpora el sistema operativo, sino con la cantidad de usuarios que lo utilizan
todos los días haciéndolo un blanco más evidente. Windows, bien, incorpora mecanismos
como Secure Boot, para proteger la imágen de arranque del sistema de modificaciones,
Windows Credential Guard, para el almacenamiento encriptado de claves y elementos
sensibles, Windows Defender (Windows Security) como antivirus, para prevenir y 
eliminar los distintos softwares maliciosos que pudieran tocar nuestro equipo, 
entre otros más como Windows Hello, un nuevo sistema de autenticación facial, y
la inclusión del software BitLocker para encriptar por completo los contenidos
del sistema de archivos primario por parte del usuario.

Apple se jacta de contar con uno de los sistemas operativos más seguros y robustos
del mercado. Esto debido a que macOS, primeramente, es un sistema operativo de 
base UNIX/BSD, por lo que hereda los mecanismos de seguridad ya mencionados
para este sistema operativo, a la vez que incluye el beneficio del exhaustivo
control sobre el hardware que ofrece Apple en sus productos, garrantizando la
seguridad gracias a su propio procesador M1. También, el sistema operativo se
protege mediante la implementación de FileVault, una encriptación total del 
sistema de archivos, y distintos candados de seguridad ligados a éste. Otro
elemento de seguridad es la Mac App Store, que cuenta con minuciosas auditorías
de seguridad para todo el software que ahí se oferta, beneficiando a todo el 
sistema operativo en general.

Para su sistema operativo móvil, iOS, Apple se ha encargado de dotarlo de diversos
mecanismos de seguridad tanto a nivel software como hardware. Algunos de ellos
son TouchID, el sensor de huellas dactilares incluído en la mayoría de los
dispositivos modernos con iOS. Se incluye un chip de encriptación y seguridad
que mantiene todo el sistema de archivos cifrado en todo momento, a su vez, y 
siguiendo con los elementos de software, iOS incorpora Secure Boot, con lo cual
vuelve difícil más no imposible a un actor modificar el sistema de arranque del
dispositivo en cuestión. A su vez, el sistema operativo cuenta con encapsulamiento
en modos de prueba para todas las aplicaciones y sus datos, así como análisis
sobre el tráfico de red para prevenir conexiones indeseadas y bloqueos automáticos
de códigos inseguros en aplicaciones mediante un estructo control en su tienda
de aplicaciones.

En el caso particular de Android, al ser un sistema operativo de base Linux, se
heredan varios mecanismos y herramientas para seguridad lo que lo vuelve un
sistema operativo bastante seguro. Sin embargo, Android, al ser un sistema
operativo orientado a los dispsitivos móviles, cuenta con particularidades como
"listener" (eventos de escucha) para prevenir código malicioso mediante mensajes
SMS, estructuras de control más rígidias en el sistema de archivos para prevenir
crear archivos en ubicaciones poco seguras o inadecuadas, manejo especial de
políticas de seguridad en preferencias del sistema, controles y candados de 
seguridad especiales para las bases de datos del sistema y aplicaciones, y,
finalmente, implementa un sistema de encriptación integrado con el cual el propio
sistema operativo no permite a los usuarios realizar cambios o adecuaciones a su
funcionamiento sin antes habilitar el modo desarrollador del mismo.

## Conclusión

Si bien los sistemas operativos modernos incluyen una vasta cantidad de herramientas
y elementos de seguridad integrados, el amplio número de vectores de ataque
así como los puntos de fallo tanto a nivel software como hardware vuelven al ramo
de ciber-seguridad uno de los más demandados actualemente en el ámbito laboral
debido a la intuición y la creatividad para descubrir nuevos errores y 
ofrecer soluciones eficaces y preventivas a los distintos riesgos de seguridad
presentes en el mundo moderno. 

