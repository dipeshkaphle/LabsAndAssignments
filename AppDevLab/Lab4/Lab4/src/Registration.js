const mongoose = require('mongoose');

const RegistrationSchema = new mongoose.Schema({
    name: {
        type: String,
        required: true
    },
    roll_no: {
        type: String,
        required: true
    },
    course: {
        type: String,
        required: true
    },
    events: [String],
    fees: {
        type: Number,
        default: 0
    }
});

const Registration = mongoose.model('Registration', RegistrationSchema);
module.exports = Registration;
