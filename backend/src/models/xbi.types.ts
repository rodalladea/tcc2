import { Document, Model } from 'mongoose';

export interface XBIInterface {
    basePicture: string | null;
    targetPicture: string | null;
    arffFile: string;
    imageDiff: number;
    chiSquared: number;
    phash: number;
    positionLeft: number;
    positionRight: number;
    positionY: number;
    visibilityLeft: number;
    visibilityRight: number;
    widthComparison: number;
    heightComparison: number;
}

export interface AllDataXBIInterface {
    arffFile: string;
    XBIs: Array<XBIInterface>;
}

export interface XBIDocument extends AllDataXBIInterface, Document {}

export type XBIInterfaceModel = Model<XBIDocument>;
