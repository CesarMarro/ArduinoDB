const express = require('express');
const router = express.Router();
const { Data } = require("../models");

// Token de Autenticación (Opcional, puedes omitirlo si no lo necesitas)
const AUTH_TOKEN = 'mi_token_secreto_123'; // Reemplaza con tu token real si usas autenticación

router.post("/", async (req, res) => {
    // Verificar el encabezado de autorización (Opcional)
    /*
    const authHeader = req.headers['authorization'];
    if (!authHeader || authHeader !== `Bearer ${AUTH_TOKEN}`) {
        return res.status(403).json({ message: "Acceso denegado" });
    }
    */

    try {
        // Asegurarse de que el cuerpo de la solicitud contenga un objeto con "value" igual a 1
        if (req.body.value === 1) {
            const newData = await Data.create({});
            res.status(201).json({ message: "Entrada creada", data: newData });
        } else {
            res.status(400).json({ message: "Datos inválidos" });
        }
    } catch (error) {
        console.error(error);
        res.status(500).json({ message: "Error del servidor" });
    }
});

module.exports = router;
