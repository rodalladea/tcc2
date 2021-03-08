import express, { Request, Response, NextFunction } from 'express';
import mongoose from 'mongoose';
import cors from 'cors';
import AppError from './errors/AppErrors';
import routes from './routes';

const app = express();
app.use(express.json());

app.use(cors());
app.use(routes);

app.use((err: Error, request: Request, response: Response, _: NextFunction) => {
    if (err instanceof AppError) {
        return response.status(err.statusCode).json({
            status: 'error',
            message: err.message,
        });
    }

    console.log(err);

    return response.status(500).json({
        status: 'error',
        message: 'Internal server error',
    });
});

mongoose.connect(
    process.env.MONGO_URL || 'mongodb://localhost:27017/tcc',
    {
        useNewUrlParser: true,
        useUnifiedTopology: true,
        useCreateIndex: true,
        useFindAndModify: false,
    },
    err => {
        if (err) {
            console.log('Could not connect to mongodb');
            process.exit(0);
        } else console.log('Connected to mongodb');
    },
);

app.listen(process.env.PORT, () => {
    console.log('Server running...');
});
