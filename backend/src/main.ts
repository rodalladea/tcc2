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
    'mongodb+srv://rodalladea:rBsC2YDvGNq3ynU@cluster0.amaro.mongodb.net/tcc2?authSource=admin&replicaSet=Cluster0-shard-0&readPreference=primary&appname=MongoDB%20Compass&ssl=true',
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
