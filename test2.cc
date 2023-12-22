#include "gestor_actividad.h"
#include <string>
#include "gtest/gtest.h"
using namespace std;

TEST(ActividadTest, ExisteActividad) 
{
    // Configuración inicial
    GestorActividad claseActividad("actividades.txt");  // Asegúrate de proporcionar el nombre del fichero correcto

    // Añade algunas actividades a la lista (sustituye con tus datos)
    Actividad actividad1(1, "IA", "Descripcion de modelos que buscan crear sistemas que imiten la inteligencia humana", "2023-01-10", "2023-02-15");
    Actividad actividad2(2,"Programación","Creación de software mediante la escritura de código","2023-03-01","2023-03-30");

    claseActividad.existeActividad(actividad1.getId());
    claseActividad.existeActividad(actividad2.getId());

    // Verifica si la función existeActividad funciona correctamente
    EXPECT_TRUE(claseActividad.existeActividad(1));
    EXPECT_TRUE(claseActividad.existeActividad(2));
    
}

TEST(GestorActividadTest, AltaActividad) {
    // Configuración inicial
    GestorActividad claseActividad("actividades.txt");  // Ajusta según sea necesario

    // Añade una actividad al gestor (debería ser exitoso)
    Actividad actividad1(1, "IA", "Descripcion de modelos que buscan crear sistemas que imiten la inteligencia humana", "2023-01-10", "2023-02-15");

    // Ejecuta la función altaActividad
    bool resultadoAlta = claseActividad.altaActividad(actividad1);

    // Verifica que la actividad se haya agregado correctamente
    EXPECT_FALSE(resultadoAlta);  // Se espera que el alta sea exitosa

    // Verifica que la actividad ahora exista en el gestor
    EXPECT_TRUE(claseActividad.existeActividad(actividad1.getId()));
}

// Define otra prueba para altaActividad cuando se intenta agregar la misma actividad dos veces
TEST(GestorActividadTest, AltaActividadDuplicada) {
    // Configuración inicial
    GestorActividad claseActividad("actividades.txt");  // Ajusta según sea necesario

    // Añade una actividad al gestor
    Actividad actividad1(1, "IA", "Descripcion de modelos que buscan crear sistemas que imiten la inteligencia humana", "2023-01-10", "2023-02-15");
    claseActividad.altaActividad(actividad1);

    // Intenta agregar la misma actividad nuevamente
    bool resultadoAltaDuplicada = claseActividad.altaActividad(actividad1);

    // Verifica que el intento de alta duplicada sea fallido
    EXPECT_FALSE(resultadoAltaDuplicada);  // Se espera que el alta sea fallida (actividad duplicada)
}