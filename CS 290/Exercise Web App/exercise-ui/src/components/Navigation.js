import React from 'react';
import { Link } from 'react-router-dom';

function Navigation() {
    return (
        <nav>
            <Link className="nav a" to="/">Home</Link>
            <Link className="nav a" to="/create-exercise">Create Exercise</Link>
        </nav>
    );
}

export default Navigation;