import * as exercises from './exercise_model.mjs';
import express from 'express';

const PORT = 3000;

const app = express();

app.use(express.json());

// Create using POST /exercises
app.post('/exercises', (req, res) => {
    exercises.createExercise(req.body.name, req.body.reps, req.body.weight, req.body.unit, req.body.date)
        .then(exercise => {
            res.status(201).json(exercise);
        })
        .catch(error => {
            console.error(error);
            res.status(500).json({ Error: `Request failed with error: ${error}` });
        });
});


// Read using GET
app.get('/exercises', (req, res) => {
    exercises.findExercises()
        .then(exercises => {
            res.status(200).send(exercises);
        })
        .catch(error => {
            console.error(error);
            res.status(500).json({ Error: `Request failed with error: ${error}` });
        });
});


// Update using PUT
app.put('/exercises/:_id', (req, res) => {
    exercises.updateExercise(req.params._id, req.body.name, req.body.reps, req.body.weight, req.body.unit, req.body.date)
        .then(numUpdated => {
            if(numUpdated === 1){
                res.status(200).json({_id: req.params._id, name: req.body.title, reps: req.body.reps, weight: req.body.weight, unit: req.body.unit, date: req.body.date})
            } else {
                res.status(404).json({ Error: 'Resource not found'});
            }
        })
        .catch(error =>{
            console.error(error);
            res.status(500).json({ Error: `Request failed with error: ${error}` });
        });
});


// Delete using DELETE
app.delete('/exercises/:_id', (req, res) => {
    exercises.deleteById(req.params._id)
        .then(deletedCount => {
            if (deletedCount === 1) {
                res.status(204).send();
            } else {
                res.status(404).json({ Error: 'Resource not found' });
            }
        })
        .catch(error => {
            console.error(error);
            res.status(500).json({ Error: `Request failed with error: ${error}` });
        });
});


app.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}...`);
})