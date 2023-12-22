#include "gestor_inscripcion.h"
#include "gtest/gtest.h"

TEST(InscripcionesActividadTest, ModificarFechaInicioCurso)
{
    inscripciones_actividad actividad("inscritos.txt"); // Asegúrate de que el nombre del archivo sea correcto
    actividad.modificarFechaInicioCurso("Usuario1", 1, "2024-01-20");
    // Agrega más expectativas según sea necesario
}

TEST(InscripcionesActividadTest, DarDeBajaUsuario)
{
    inscripciones_actividad actividad("inscritos.txt"); // Asegúrate de que el nombre del archivo sea correcto
    bool bajaExitosa = actividad.darDeBajaUsuario("Usuario2", 2);
    EXPECT_FALSE(bajaExitosa);
}

TEST(InscripcionesActividadTest, FechaInscripcionEnRango)
{
    inscripciones_actividad actividad("inscritos.txt"); // Asegúrate de que el nombre del archivo sea correcto

    // Supongamos que tenemos una inscripción con ID 3 en el archivo de inscripciones
    bool enRango = actividad.fechaInscripcionEnRango(3, "2024-01-01", "2024-03-01");
    EXPECT_FALSE(enRango);

    // Prueba con valores fuera del rango
    enRango = actividad.fechaInscripcionEnRango(2, "2024-01-01", "2024-02-01");
    EXPECT_FALSE(enRango);
    
}