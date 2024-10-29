const express = require('express');
const app = express();

const db = require('./models');

// Middleware para parsear JSON
app.use(express.json());

const dataRouter = require('./routes/Data');
app.use("/data", dataRouter);

// Sincronizar la base de datos y comenzar a escuchar en todas las interfaces
db.sequelize.sync().then(() => {
    app.listen(3001, '0.0.0.0', () => { // Asegura que el servidor escuche en todas las interfaces
        console.log("--------------Servidor corriendo en el puerto 3001-------------");
    });
});
