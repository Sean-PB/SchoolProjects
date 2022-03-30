import './App.css';
import React, {useState} from 'react';
import { BrowserRouter as Router, Route } from 'react-router-dom';
import HomePage from './pages/HomePage';
import CreateExercisePage from './pages/CreateExercisePage';
import EditExercisePage from './pages/EditExercisePage';
import Navigation from './components/Navigation.js'
import { IoBarbell } from 'react-icons/io5';


function App() {
  const [exerciseToEdit, setExerciseToEdit] = useState();

  return (
    <div className="App">
      <Router>
        <header>
          <IoBarbell className="icon"/>
          <h1>Exercise Tracker</h1>
          <p>Use this web application to create and track your exercises!</p>
        </header>

        <Navigation className="Nav"/>
        
        <main>
          <Route path="/" exact>
            <HomePage setExerciseToEdit={setExerciseToEdit} />
          </Route>
          <Route path="/create-exercise">
            <CreateExercisePage />
          </Route>
          <Route path="/edit-exercise">
            <EditExercisePage exerciseToEdit={exerciseToEdit} />
          </Route>
        </main>

        <footer>
          <p>&copy; 2022 Sean Brandon</p>
        </footer>

      </Router>
    </div> 
  );
}

export default App;
