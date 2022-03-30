import React from 'react';
import { MdDeleteForever, MdEdit } from 'react-icons/md';

function Exercise({ exercise, onDelete, onEdit }) {
    return (
        <tr>
            <td>{exercise.name}</td>
            <td>{exercise.reps}</td>
            <td>{exercise.weight}</td>
            <td>{exercise.unit}</td>
            <td>{exercise.date}</td>
            <td className="item-button" onClick={ () => onEdit(exercise) } >< MdEdit  /></td>
            <td className="item-button" onClick={ () => onDelete(exercise._id) } >< MdDeleteForever /></td>
        </tr>
    );
}

export default Exercise;