# Usine du future
Projet usine du futur de 4ème année à l'ENSIM des étudiants ASTRE. 

Le projet utilise une firebeetle 2 esp32e.

Le code est réaliser via platerformIO. Il s'agit d'une extension instalable sur VScode. 
[Pour plus d'information](https://platformio.org)

# Problème connue
Il y a une erreur à la compilation lié à une bibliothèque. Il faut donc modifié une ligne de code dans la bibliothèque pour que cela puisse compilé. Pour cela, 
aller dans .pio/libdeps/dfrobot_firebeetle2_esp32e/AnyRtttl/src/anyrtttl.cpp et changer la ligne suivante: DelayFuncPtr _delay = &delay; en DelayFuncPtr _delay = (void (*)(long unsigned int))(&delay);

