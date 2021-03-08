import { Schema } from 'mongoose';

const XBISchema = new Schema({
    arffFile: String,
    XBIs: [
        {
            basePicture: String,
            targetPicture: String,
            arffFile: String,
            imageDiff: Number,
            chiSquared: Number,
            phash: Number,
            positionLeft: Number,
            positionRight: Number,
            positionY: Number,
            visibilityLeft: Number,
            visibilityRight: Number,
            widthComparison: Number,
            heightComparison: Number,
        },
    ],
});

export default XBISchema;
