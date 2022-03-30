import mongoose from 'mongoose';

mongoose.connect(
    "mongodb://localhost:27017/exercise_db",
    { useNewUrlParser: true, useUnifiedTopology: true }
);

// Connect to the database
const db = mongoose.connection;
// Open once the database connection is successfully opened
db.once("open", () => {
    console.log("Successfully connected to MongoDB using Mongoose!");
});

// Schema
const exerciseSchema = mongoose.Schema({
    name: {type: String, required: true },
    reps: {type: Number, required: true },
    weight: {type: Number, required: true },
    unit: {type: String, required: true },
    date: {type: String, required: true },
});

// Compile the model from the schema. Must be done after defining the schema
const Exercsise = mongoose.model("Exercise", exerciseSchema);

// Create Exercise
const createExercise = async (name, reps, weight, unit, date) => {
    const exercise = new Exercsise({name: name, reps: reps, weight: weight, unit: unit, date: date});
    return exercise.save();
}

// Find Exercise
const findExercises = async () => {
    const query = Exercsise.find()
    return query.exec();
}

// Replace Exercise
const updateExercise = async (id, name, reps, weight, unit, date) => {
    const result = await Exercsise.replaceOne({_id: id}, {name: name, reps: reps, weight: weight, unit: unit, date: date});
    return result.modifiedCount;
}

// Delete Exercise
const deleteById = async (id) => {
    const result = await Exercsise.deleteOne({_id: id});
    return result.deletedCount;
}

export {createExercise, findExercises, updateExercise, deleteById}